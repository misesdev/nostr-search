import SearchHeader from '@/components/SearchHeader';
import './../globals.css';

export default function layout({ children }: any) {
    return (
        <div className="bg-gray-900 pb-4">
            <SearchHeader />
            {children}
        </div>
    );
}
