
export const RelayLoading = () => {
    return (
        <div className='w-full group'>
            <div className="p-5 bg-gray-800 rounded-3xl overflow-x-clip">
                <div className='max-w-6xl animate-pulse'>
                    <div className="w-full flex">
                        <div className='w-[80px] h-[80px] bg-gray-200 rounded-[13px] mb-2.5'></div>
                        <div className='mx-6 h-[50px] w-[220px] lb:w-[80px] bg-gray-200 rounded-[20px] mb-2.5'></div>
                    </div>
                </div>
                <div className='max-w-6xl animate-pulse'>
                    <div className='h-2.5 w-48 bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-2.5 w-[120px] lb:w-[230px] bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-2.5 w-[290px] lb:w-[530px] bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-2.5 w-48 bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
                    <div className='h-3.5 w-[300px] lb:w-[360px] bg-gray-200 rounded-full mb-2.5'></div>
                </div>
            </div>
        </div>
    )
}
