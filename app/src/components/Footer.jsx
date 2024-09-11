import CountryLookup from './CountryLookup';

export default function Footer() {
    return (
        <footer className='absolute bottom-0 text-sm text-gray-500 bg-[#f2f2f2] w-full'>
            <div className='border-b px-8 py-3'>
                <CountryLookup />
            </div>
        </footer>
    );
}
